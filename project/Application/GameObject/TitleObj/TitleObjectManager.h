#pragma once

#include <memory>
#include <string>
#include <vector>
#include "TO_Base.h"
#include "TCamera/TO_Camera.h"
#include "TPlayer/TO_Player.h"
#include "TStatic/TO_StaticObj.h"
#include "TVehicle/TO_Vehicle.h"

class TitleObjectManager
{
 public:
   TitleObjectManager() = default;
   ~TitleObjectManager() = default;

   void Init();
   void Update();
   void ImGuiUpdate();
   void Clear();

 private:
   std::unique_ptr<TO_Camera> camera_;
   std::vector<std::unique_ptr<TO_Base>> updatableObjects_;
   std::vector<std::unique_ptr<TO_Base>> staticObjects_;
};
