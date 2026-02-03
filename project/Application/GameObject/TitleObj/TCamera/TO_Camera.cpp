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
      transform.translate = {0.0f, 40.0f, -60.0f};
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
   if (!cameraData)
      return;

   // カメラごとのツリーを作成
   if (ImGui::TreeNode(targetName_.c_str())) {
      auto &transform = cameraData->GetWorldTransform().transform;

      // 座標の操作 (ドラッグで数値を変更、速度0.1f)
      ImGui::DragFloat3("Translate", &transform.translate.x, 0.1f);

      // 回転の操作
      ImGui::DragFloat3("Rotate", &transform.rotate.x, 0.01f);

      // リセットボタン
      if (ImGui::Button("Reset")) {
         transform.translate = {0.0f, 0.0f, 0.0f};
         transform.rotate = {0.0f, 0.0f, 0.0f};
      }

      ImGui::TreePop();
   }
}
