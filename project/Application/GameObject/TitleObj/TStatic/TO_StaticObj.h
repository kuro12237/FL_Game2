#pragma once

#include "../TO_Base.h"

class TO_StaticObj : public TO_Base
{
 public:
   TO_StaticObj() = default;
   TO_StaticObj(const std::string &name);
   ~TO_StaticObj() override = default;

   void Initialize() override;
   void Update() override {}
};
