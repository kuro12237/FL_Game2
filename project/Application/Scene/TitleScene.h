#pragma once
#include "GameManager.h"
#include <memory>

#include "GameObject/TitleCamera/TitleCamera.h"
#include "GameObject/TitleObj/TitleObjectManager.h"
#include "GameObject/TitleSpr/TitleSpriteManager.h"

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
   unique_ptr<TitleObjectManager> toMgr_;
   unique_ptr<TitleSpriteManager> tsMgr_;
};
