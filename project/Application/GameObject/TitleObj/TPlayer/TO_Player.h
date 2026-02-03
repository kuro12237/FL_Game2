#pragma once

#include "../TO_Base.h"

class TO_Player : public TO_Base
{
 public:
   TO_Player() = default;
   TO_Player(const std::string &name);
   ~TO_Player() = default;

   void Initialize() override;
   void Update() override;

 private:
   void UpdateTransform();
   void RotateUpdate();

 private:
   Math::Vector::Vector3 velocity_{};
   bool isGrounded_ = false;

   float speed_ = 0.05f;  // 走る速度
   float limitX_ = 20.0f; // 折り返すx座標の端

   float swingTimer_ = 0.0f;  // 体を振るためのタイマー
   float swingSpeed_ = 10.0f; // 振る速さ
   float swingAngle_ = 0.1f;  // 振る角度（ラジアン）
};
