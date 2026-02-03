#pragma once

#include "../TO_Base.h"

class TO_Vehicle : public TO_Base
{
 public:
   TO_Vehicle() = default;
   TO_Vehicle(const std::string &name);
   ~TO_Vehicle() override = default;

   void Initialize() override;
   void Update() override;

 protected:
   Math::Vector::Vector3 velocity_{};
};
