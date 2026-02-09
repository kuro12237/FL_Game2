#pragma once

#include "../TO_Base.h"

class TO_Camera : public TO_Base
{
 public:
   TO_Camera(const std::string &name);
   ~TO_Camera() override = default;

   void Initialize() override;
   void Update() override;
   void ImGuiUpdate();

    // ===== 追加 =====
   void SetTranslate(const Math::Vector::Vector3 &t);
   void SetRotate(const Math::Vector::Vector3 &r);
   void SetTransform(const Math::Vector::Vector3 &t, const Math::Vector::Vector3 &r);

 private:
   float speed_ = 0.0f;
   bool isCameraMove_ = true;
};