#pragma once
#include <memory>
#include "Cleyera.h"
#include "GameManager.h"
#include "GameObject/TitleCamera/TitleCamera.h"
#include "GameObject/TitleObj/TLight/TO_Light.h"
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
   unique_ptr<TO_Light> light_;
   unique_ptr<TitleObjectManager> toMgr_;
   unique_ptr<TitleSpriteManager> tsMgr_;

   bool isPushed_ = false;
};