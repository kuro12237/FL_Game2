#include "GoalHouseManager.h"

void GoalHouseManager::Initialize()
{

   // auto &transforms = GameObjectManager::GetInstance()->GetObj3dData(name_);

   for (int i = 0; i < int(1); i++) {
      shared_ptr<GoalHouse> block = make_shared<GoalHouse>();

      block->SetName(name_);
      block->SetUnitIndex(i);
      block->Initialize();
      blocks_.push_back(block);
      objDataList_.push_back(block);
   }

}

void GoalHouseManager::Update()
{
   for (shared_ptr<GoalHouse> &b : blocks_) {

      if (*blockNum_ == 0) {
         b->SetisPackageComp(true);


          if (b->GetIsClear()) {

            isClear_ = true;
         }
      }
      b->Update();
   }
}
