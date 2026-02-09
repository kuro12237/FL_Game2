#include "TO_Vehicle.h"

TO_Vehicle::TO_Vehicle(const std::string &name) 
{
   TO_Base::SettTargetName(name);
}

void TO_Vehicle::Initialize() 
{
   Bind2ExistingObj3D(); 

   velocity_ = kSpeed;

   auto obj = objectData_.lock();
   if (obj) {
      baseY_ = obj->GetWorldTransform().transform.translate.y;
   }
}

void TO_Vehicle::Update() 
{
   auto obj = objectData_.lock();
   if (!obj)
      return;

   auto &tr = obj->GetWorldTransform().transform;

   // X移動＋ラップ（Playerと完全一致）
   tr.translate.x += velocity_;
   if (tr.translate.x > kLimitX)
      tr.translate.x = -kLimitX;
   if (tr.translate.x < -kLimitX)
      tr.translate.x = kLimitX;

   // 位相ずらし（Vehicle：遅れ＆弱め）
   time_ += 1.0f / 60.0f;
   tr.translate.y = baseY_ + std::sin(time_ * kBobSpeed + 1.2f) * (kBobAmp * 0.5f);
}
