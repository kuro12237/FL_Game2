#pragma once
#include "Cleyera.h"
#include <memory>
#include <vector>

class StageSelect
{
 public:
   StageSelect() = default;
   ~StageSelect() = default;

   void Init();
   void Update();
   void Draw();
   void ImGuiUpdate();

   int GetSelectedStage() const { return selectedStage_; }

 private:
   struct StageButton
   {
      int stage = 0;
      std::unique_ptr<Engine::Objects::Sprite> sprite;
      Engine::Transform::WorldTransform transform;
   };

    void CreateButtons();
   void ApplyUV(StageButton &btn);
   void UpdateCursor();

 private:
   std::vector<StageButton> buttons_;

   uint32_t atlasTex_ = 0;

   int cursor_ = 0;        // 0〜9
   int selectedStage_ = 1; // 1〜10
   int inputWait_ = 0;
};
