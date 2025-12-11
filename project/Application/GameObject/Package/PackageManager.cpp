#include "PackageManager.h"

void PackageManager::Initialize()
{

   // 後でサイズ設定
   for (int i = 0; i < 1; i++) {
      shared_ptr<Package> package = make_shared<Package>();

      package->SetName(name_);
      package->SetUnitIndex(i);
      package_.push_back(package);
      objDataList_.push_back(package);
   }

   for (auto &it : objDataList_) {
      auto obj = it.lock();
      obj->Initialize();
   }
}

void PackageManager::Update()
{

   for (shared_ptr<Package> &b : package_) {
      if (!b)
         continue;

      if (b->GetIsDead()) {

         gameObjectManager_->ClearObj3dData(b->GetName());
         b.reset();
         num_--;
         continue; // ← ここで次へ進む
      }

      b->Update();
   }
}
