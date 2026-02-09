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
   float velocity_ = 0.0f;
   float time_ = 0.0f;
   float baseY_ = 0.0f;
};
