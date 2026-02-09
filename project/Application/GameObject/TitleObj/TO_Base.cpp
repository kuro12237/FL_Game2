#include "TO_Base.h"

void TO_Base::Bind2ExistingObj3D()
{
   gameObjectManager_ = GameObjectManager::GetInstance();
   objectData_ = gameObjectManager_->GetObj3dData(targetName_);
   INameable::name_ = targetName_;
} 