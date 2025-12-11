#include "Package.h"

void Package::Initialize()
{
   auto &transforms = gameObjectManager_->GetObj3dData(name_)->GetWorldTransform();

   // dataをセット
   collider_->SetOnCollisionFunc(std::bind(&ObjectComponent::OnCollision, this, std::placeholders::_1));

   collider_->SetObjectData(transforms.transform);
   collider_->SetAABB({{-1.0f, -1.0f, -1.0f}, {1.0f, 1.0f, 1.0f}});

   collider_->SetId(ObjectId::kPackageId);
   collider_->SetMask(CollisionMask::kBlockMask);
   collider_->SetAttribute(CollisionMask::kBlockAttribute);
   objectData_ = gameObjectManager_->GetObj3dData(INameable::name_);
}

void Package::Update()
{
   if (!playerPos_)
      return;

   if (isPlayerHit_) {
      auto &transform = objectData_.lock()->GetWorldTransform().transform;

      if (transform.translate.x > playerPos_->x) {
         transform.translate.x = playerPos_->x + 2.00001f;
      }
      else {
         transform.translate.x = playerPos_->x - 2.00001f;
      }
      isPlayerHit_ = false;
   }
}

void Package::OnCollision([[maybe_unused]] ObjectComponent *objData)
{

   auto c = objData->GetCollider();

   if (c->GetId() == ObjectId::kPlayerId) {

      isPlayerHit_ = true;
      playerPos_ = &objData->GetObjectData().lock()->GetWorldTransform().transform.translate;

      auto &transform = objectData_.lock()->GetWorldTransform().transform;

      if (transform.translate.x > playerPos_->x) {
         transform.translate.x = playerPos_->x + 2.00001f;
      }
      else {
         transform.translate.x = playerPos_->x - 2.00001f;
      }


   }

   if (c->GetId() == ObjectId::kNormalBlock) {
      for (auto &hitDirection : collider_->GetHItDirection()) {
         if (hitDirection == TOP && velocity_.y >= 0.0f) {
            velocity_ = {};
         }
         if (hitDirection == BOTTOM && velocity_.y <= -0.0f) {
            velocity_ = {};
         }
      }

      auto &transform = objectData_.lock()->GetWorldTransform().transform;

      transform.translate.x += collider_->GetExtrusion().x;
      transform.translate.y += collider_->GetExtrusion().y;
   }
}
