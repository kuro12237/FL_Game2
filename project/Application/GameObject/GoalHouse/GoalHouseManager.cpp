#include "GoalHouseManager.h"

void GoalHouseManager::Initialize()
{

   auto &transforms = GameObjectManager::GetInstance()->GetObjInstancingData(name_)->GetTransforms();

   for (int i = 0; i < int(transforms.size()); i++) {
      shared_ptr<GoalHouse> block = make_shared<GoalHouse>();

      block->SetName(name_);
      block->SetUnitIndex(i);
      block->Initialize();
      blocks_.push_back(block);
   }
}

void GoalHouseManager::Update()
{

   for (shared_ptr<GoalHouse> &b : blocks_) {
      b->Update();
   }
}
