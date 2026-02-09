#pragma once
#include "Cleyera.h"
#include <memory>
#include <string>
#include <vector>

class GamePlayOperationUIManager
{
 public:
   GamePlayOperationUIManager() = default;
   ~GamePlayOperationUIManager() = default;

   void Init();
   void Update();
   void Draw();
   void Clear();

   // 状態制御
   void SetVisible(bool visible);

 private:
   struct UISpriteItem
   {
      std::unique_ptr<Engine::Objects::Sprite> sprite;
      Engine::Transform::WorldTransform transform;
      std::string name;
      bool visible = true;
   };

   std::vector<UISpriteItem> sprites_;
   bool isVisible_ = true;
};