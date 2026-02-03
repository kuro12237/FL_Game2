#include "TO_Player.h"

TO_Player::TO_Player(const std::string &name) : TO_Base()
{
   TO_Base::SettTargetName(name);
}

void TO_Player::Initialize()
{
   TO_Base::Bind2ExistingObj3D();

   // 最初は右向きに動き出す設定
   //velocity_.x = speed_;
}

void TO_Player::Update() 
{
   //swingTimer_ += swingSpeed_;
   //UpdateTransform();
   //RotateUpdate();
}

void TO_Player::UpdateTransform() 
{
   // TO_Base::objectData_ を使用
   auto &transform = objectData_.lock()->GetWorldTransform().transform;

   // 1. 左右の端に来たら速度を反転させる
   if (transform.translate.x > limitX_) {
      velocity_.x = -speed_;
   }
   else if (transform.translate.x < -limitX_) {
      velocity_.x = speed_;
   }

   // 2. 座標更新
   transform.translate.x += velocity_.x;
}

void TO_Player::RotateUpdate()
{
   auto &transform = objectData_.lock()->GetWorldTransform().transform;

   const float degrees = 90.0f;
   float radian = 0.0f;

   if (velocity_.x > 0.0f) {
      radian = Math::Vector::degreesToRadians(degrees);
      transform.rotate.y = radian;
   }
   else if (velocity_.x < 0.0f) {
      radian = Math::Vector::degreesToRadians(-degrees);
      transform.rotate.y = radian;
   }

   // --- 急いでいる演出：Z軸を左右に振る ---
   transform.rotate.z = std::sin(Math::Vector::degreesToRadians(swingTimer_)) * swingAngle_;
}