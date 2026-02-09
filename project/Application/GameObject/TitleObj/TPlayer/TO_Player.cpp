#include "TO_Player.h"

TO_Player::TO_Player(const std::string &name) : TO_Base()
{
   TO_Base::SettTargetName(name);
}

void TO_Player::Initialize()
{
   Bind2ExistingObj3D(); 

   velocity_ = kSpeed;

   auto obj = objectData_.lock();
   if (obj) {
      baseY_ = obj->GetWorldTransform().transform.translate.y;
   }
}

void TO_Player::Update() 
{
   auto obj = objectData_.lock();
   if (!obj)
      return;

   auto &tr = obj->GetWorldTransform().transform;

   // X移動＋ラップ
   tr.translate.x += velocity_;
   if (tr.translate.x > kLimitX)
      tr.translate.x = -kLimitX;
   if (tr.translate.x < -kLimitX)
      tr.translate.x = kLimitX;

   // 位相ずらし（Player：先行）
   time_ += 1.0f / 60.0f;
   tr.translate.y = baseY_ + std::sin(time_ * kBobSpeed + 0.0f) * kBobAmp;
}
