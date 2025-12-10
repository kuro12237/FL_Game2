#include "PackageManager.h"

void PackageManager::Initialize() {

   auto &transforms = GameObjectManager::GetInstance()->GetObjInstancingData(name_)->GetTransforms();

   for (int i = 0; i < int(transforms.size()); i++) {
      shared_ptr<Package> package = make_shared<Package>();

      package->SetName(name_);
      package->SetUnitIndex(i);
      package->Initialize();
      package_.push_back(package);
   }
}

void PackageManager::Update() {


   for (shared_ptr<Package> &b : package_) {
      b->Update();
   }
}
