#pragma once
#include "GameManager.h"
#include <memory>

#include "GameObject/TitleCamera/TitleCamera.h"

class TitleScene : public IScene
{
 public:
   TitleScene();
   ~TitleScene() = default;

   void Initialize(GameManager *state) override;
   void Update([[maybe_unused]] GameManager *Scene) override;
   void ImGuiUpdate() override;
   void PostProcessDraw() override;
   void Flont2dSpriteDraw() override;

 private:
   shared_ptr<TitleCamera> camera_ = nullptr;
};
