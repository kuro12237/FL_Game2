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

    bool IsLJoystickRight();
   bool IsLJoystickLeft();
    bool IsLJoystickUp();
    bool IsLJoystickDown();

 private:
   std::vector<StageButton> buttons_;

   uint32_t atlasTex_ = 0;

   int cursor_ = 0;        // 0〜9
   int selectedStage_ = 1; // 1〜10
   int inputWait_ = 0;

    int currentIndex_ = 0;
   const float M_PI = 3.14159265358979323846f;
   float joystickThreshold_ = 0.8f;
   // 前フレーム状態
   bool prevRight_ = false;
   bool prevLeft_ = false;
   bool prevUp_ = false;
   bool prevDown_ = false;
};
