#include "Package.h"

void Package::Initialize() {
   auto &transforms = gameObjectManager_->GetObjInstancingData(name_)->GetTransforms()[unitNumber_];

   // dataをセット
   collider_->SetOnCollisionFunc(std::bind(&ObjectComponent::OnCollision, this, std::placeholders::_1));

   collider_->SetObjectData(transforms->GetTransform());
   collider_->SetAABB(transforms->GetAABB());
   collider_->SetId(ObjectId::kPackageId);
   collider_->SetMask(CollisionMask::kBlockMask);
   collider_->SetAttribute(CollisionMask::kBlockAttribute);
}

void Package::Update() {}

void Package::OnCollision(ObjectComponent *objData) {}
