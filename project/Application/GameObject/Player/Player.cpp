#include "Player.h"

using namespace Engine;
using namespace Engine::Objects;
using namespace Engine::Manager;
using namespace Engine::Transform;

void Player::Initialize()
{
   INameable::name_ = "PlayerCore";
   jsonGropName_ = INameable::name_;
   CreateJsonData();

   // dataをセット
   objectData_ = gameObjectManager_->GetObj3dData(INameable::name_);

   // コライダーセット
   this->SetColliderParamData();
   collider_->SetId(ObjectId::kPlayerId);
   collider_->SetIsExtrusion(true);
   collider_->SetMask(CollisionMask::kPlayerMask);
   collider_->SetAttribute(CollisionMask::kPlayerAttribute);

   // TransformGet
   auto &transform = objectData_.lock()->GetWorldTransform().transform;

   // Scale値を外部から読み込む
   float dfScale = 0.3f;
   // AddJsonItem<float>("DefaultScale", dfScale);
   // dfScale = GetJsonItem<float>("DefaultScale");
   transform.scale = {dfScale, dfScale, dfScale};

   // スタート入りの記録
   resetPos_ = transform.translate;
   AnimationManager::GetInstance()->LoadAnimation("FallDown");
}

void Player::ImGuiUpdate()
{
   string imguiTreeName = INameable::name_ + "core";
   if (ImGui::TreeNode(imguiTreeName.c_str())) {
      if (ImGui::Button("Reset")) {
         velocity_ = {};
      }

      ImGui::Text("%d", static_cast<int>(states_.size()));

      ImGui::TreePop();
   }
}

void Player::Update()
{
   auto &objData = gameObjectManager_->GetObj3dData(INameable::name_);

   shootTimerFlame_++;

   // 状態更新
   for (auto &state : states_) {
      auto &it = state.second;
      if (it) {
         it->Update(this);
      }
   }
   objData->GetGameObject()->SkeletonUpdate();

   // 更新後にキューから状態を削除
   while (!statesToRemoveQueue_.empty()) {
      std::type_index typeIdx = statesToRemoveQueue_.front();
      states_.erase(typeIdx);
      statesToRemoveQueue_.pop();
   }

   TransformUpdate();

   // TransformEular &transform = objData->GetWorldTransform().transform;

   RotateUpdate();

   AABB aabb;
   aabb.max = {1.0f, 2.0f, 1.0f};
   aabb.min = {1.0f, -2.0f, 1.0f};
   collider_->SetAABB(aabb);

   collider_->ClearExtrusion();
   collider_->ClearHitDirection();
}

void Player::OnCollision([[maybe_unused]] ObjectComponent *objData)
{
   auto c = objData->GetCollider();

   /* if (ObjectId::kOnlyCollideWithBlocksid) {
       return;
    }*/

   if (c->GetId() == ObjectId::kPlayerId) {

      return;
   }

   if (c->GetId() == ObjectId::kPackageId) {
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

void Player::RotateUpdate()
{
   TransformEular &transform = gameObjectManager_->GetObj3dData(INameable::name_)->GetWorldTransform().transform;

   const float degrees = 90.0f;
   float radian = 0.0f;
   if (velocity_.x > 0.0f) {
      radian = Math::Vector::degreesToRadians(degrees);
      transform.rotate.y = radian;
   }
   // 左
   if (velocity_.x < 0.0f) {
      radian = Math::Vector::degreesToRadians(-degrees);
      transform.rotate.y = radian;
   }
}

void Player::Jamp()
{

   CheckStatePush<PlayerStateDeadAnimation>();

   if (IsCheckStateRetuen()) {
      return;
   }

   if (!IsInState<PlayerStateJamp>() && velocity_.y == 0.0f) {
      AddState<PlayerStateJamp>();
   }
}

void Player::Move()
{

   CheckStatePush<PlayerStateDeadAnimation>();
   CheckStatePush<PlayerStateDash>();

   if (IsCheckStateRetuen()) {
      return;
   }

   if (!IsInState<PlayerStateWalk>()) {
      AddState<PlayerStateWalk>();
   }
}

void Player::Shoot()
{
   if (shootTimerFlame_ >= shootTimerMax_) {
      isShoot_ = true;
      shootTimerFlame_ = 0;
   }
}

void Player::Dash()
{
   // 指定のステートの場合通さない
   CheckStatePush<PlayerStateDeadAnimation>();
   CheckStatePush<PlayerStateFall>();
   CheckStatePush<PlayerStateJamp>();
   if (IsCheckStateRetuen()) {
      return;
   }

   // 歩きののとき削除
   if (IsInState<PlayerStateWalk>()) {
      MarkStateForRemoval<PlayerStateWalk>();
   }

   // ダッシュがなかったら追加
   if (!IsInState<PlayerStateDash>()) {
      AddState<PlayerStateDash>();
   }
}

void Player::Aim()
{
   isAim_ = true;
   // 指定のステートの場合通さない
   CheckStatePush<PlayerStateDeadAnimation>();
   CheckStatePush<PlayerStateFall>();
   CheckStatePush<PlayerStateJamp>();

   if (IsCheckStateRetuen()) {
      return;
   }
}

void Player::TransformUpdate()
{
   TransformEular &transform = objectData_.lock()->GetWorldTransform().transform;

   transform.translate = Math::Vector::Add(transform.translate, velocity_);
}
