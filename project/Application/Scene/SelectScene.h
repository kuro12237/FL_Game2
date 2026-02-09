#pragma once
#include <memory>

#include "Cleyera.h"
#include "GameManager.h"

#include "ChangeSceneAnimation/ChangeSceneAnimation.h"

#include "GameObject/TitleCamera/TitleCamera.h"
#include "GameObject/TitleObj/TLight/TO_Light.h"
#include "GameObject/TitleObj/TitleObjectManager.h"

#include "GameObject/StageSelect/StageSelect.h"

#include "GameObject/SceneContextData/SceneContextData.h"
#include "ISceneContext.h"

#include "Scene/GameScene.h"

/// <summary>
/// Stage Select Scene
/// </summary>
class SelectScene : public IScene
{
 public:
   SelectScene();
   ~SelectScene() = default;

   void Initialize(GameManager *state) override;
   void Update(GameManager *Scene) override;
   void ImGuiUpdate() override;
   void PostProcessDraw() override;
   void Flont2dSpriteDraw() override;

 private:
   // Title と同じ構成
   std::unique_ptr<TO_Light> light_;
   std::unique_ptr<TitleObjectManager> toMgr_;

   // Stage Select
   std::unique_ptr<StageSelect> select_;
   bool isSelected_ = false;

   // Scene transition
   std::unique_ptr<ISceneContext> context_;
   SceneContextData contextData_;
};
