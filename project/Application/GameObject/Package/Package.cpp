#include "Package.h"

void Package::Initialize()
{
   // dataをセット
   objectData_ = gameObjectManager_->GetObj3dData(INameable::name_);

   auto &transform = gameObjectManager_->GetObj3dData(name_)->GetWorldTransform();

   // dataをセット
   collider_->SetOnCollisionFunc(std::bind(&ObjectComponent::OnCollision, this, std::placeholders::_1));
   Math::Vector::Vector2 minmax = {-2.0f, 2.0f};
   AABB aabb = {Math::Vector::Multiply(transform.transform.scale, minmax.x), Math::Vector::Multiply(transform.transform.scale, minmax.y)};


   // コライダーセット
   //this->SetColliderParamData();

   collider_->SetObjectData(transform.transform);
   collider_->SetId(ObjectId::kPackageId);
   collider_->SetIsExtrusion(true);
   collider_->SetMask(CollisionMask::kEnemyWalkMask);
   collider_->SetAttribute(CollisionMask::kEnemyWalkAttribute);

   this->isUseGravityFlag_ = true;
   objectData_ = gameObjectManager_->GetObj3dData(INameable::name_);
}

void Package::Update()
{

   Engine::Transform::TransformEular &transform = objectData_.lock()->GetWorldTransform().transform;

   transform.translate = Math::Vector::Add(transform.translate, velocity_);


   if (playerPos_) {

      if (isPlayerHit_) {
         // auto &transform = objectData_.lock()->GetWorldTransform().transform;

         isPlayerHit_ = false;
      }

      if (isWarp_) {
         if (Engine::Input::PushBottonPressed(XINPUT_GAMEPAD_B)) {

            if (transform.translate.x >= playerPos_->x) {
               transform.translate = *playerPos_;

               if (playerRotate_->y <= 0.0f) {
                  transform.translate.x += -2.00001f;
               }
               else {

                  transform.translate.x -= -2.00001f;
               }

            }
            gameObjectManager_->GetObj3dData(name_)->GetGameObject()->SetDesc({.colorDesc{.color_{1.0f, 1.0f, 1.0f, 1.0f}}});

            isWarp_ = false;
         }
      }
   }
   collider_->ClearExtrusion();
   collider_->ClearHitDirection();
}

void Package::OnCollision([[maybe_unused]] ObjectComponent *objData)
{

   auto c = objData->GetCollider();

   if (c->GetId() == ObjectId::kPlayerId) {

      isPlayerHit_ = true;
      playerPos_ = &objData->GetObjectData().lock()->GetWorldTransform().transform.translate;
      playerRotate_ = &objData->GetObjectData().lock()->GetWorldTransform().transform.rotate;

      gameObjectManager_->GetObj3dData(name_)->GetGameObject()->SetDesc({.colorDesc{.color_{0.0f, 0.0f, 1.0f, 1.0f}}});

      auto &transform = objectData_.lock()->GetWorldTransform().transform;

      isWarp_ = true;

      for (auto &hitDirection : collider_->GetHItDirection()) {

         if (transform.translate.x >= playerPos_->x && hitDirection == LEFT) {

            transform.translate.x = playerPos_->x + 2.00001f;
         }
         else if (transform.translate.x <= playerPos_->x && hitDirection == RIGHT) {
            transform.translate.x = playerPos_->x - 2.00001f;
         }
      }

      return;
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

   if (c->GetId() == ObjectId::kGoalId) {

      isDead_ = true;
   }
}
