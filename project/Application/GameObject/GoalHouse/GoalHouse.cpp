#include "GoalHouse.h"

void GoalHouse::Initialize()
{

   auto &transforms = gameObjectManager_->GetObj3dData(name_)->GetWorldTransform();

   // dataをセット
   collider_->SetOnCollisionFunc(std::bind(&ObjectComponent::OnCollision, this, std::placeholders::_1));

   collider_->SetObjectData(transforms.transform);
   collider_->SetAABB({{-1.0f, -1.0f, -1.0f}, {1.0f, 1.0f, 1.0f}});
   collider_->SetId(ObjectId::kGoalId);
   collider_->SetMask(CollisionMask::kBlockMask);
   collider_->SetAttribute(CollisionMask::kBlockAttribute);
}

void GoalHouse::Update() {}

void GoalHouse::OnCollision([[maybe_unused]] ObjectComponent *objData)
{

   auto c = objData->GetCollider();

   if (c->GetId() == ObjectId::kPlayerId) {

      isClear_ = true;
   }
}
