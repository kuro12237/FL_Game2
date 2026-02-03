#include "TitleObjectManager.h"
#include "Utility/ObjectManager/GameObjectManager.h"

void TitleObjectManager::Init()
{
   Clear();
   auto *goMgr = GameObjectManager::GetInstance();

   // --- CAMERAの構築 ---
   std::string targetCamName = "PlayerCamera";
   if (goMgr->GetCameraData(targetCamName)) {
      camera_ = std::make_unique<TO_Camera>(targetCamName);
      camera_->Initialize();
   }

   // --- MESH（3Dオブジェクト）の構築 ---
   auto &meshMap = goMgr->GetObj3dDatas();
   for (auto &[name, data] : meshMap) {
      std::unique_ptr<TO_Base> newObj = nullptr;

      if (name.find("Player") != std::string::npos) {
         // Player系
         newObj = std::make_unique<TO_Player>(name);
      }
      else if (name.find("Truck") != std::string::npos) {
         // Vehicle系
         newObj = std::make_unique<TO_Vehicle>(name);
      }
      else {
         // それ以外はすべてStatic
         newObj = std::make_unique<TO_StaticObj>(name);
      }

      if (newObj) {
         // 初期化処理
         newObj->Initialize();

         // PlayerかTruck(Vehicle)なら更新リストへ、それ以外は静的リストへ
         if (name.find("Player") != std::string::npos || name.find("Truck") != std::string::npos) {
            updatableObjects_.push_back(std::move(newObj));
         }
         else {
            staticObjects_.push_back(std::move(newObj));
         }
      }
   }
}

void TitleObjectManager::Update()
{
   camera_->Update();
   for (auto &obj : updatableObjects_) {
      obj->Update();
   }
}

void TitleObjectManager::Clear()
{
   camera_.reset();
   updatableObjects_.clear();
   staticObjects_.clear();
}
