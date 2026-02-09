#pragma once

#include <memory>
#include <string>
#include <vector>
#include "Cleyera.h"

class TitleSpriteManager
{
 public:
   TitleSpriteManager() = default;
   ~TitleSpriteManager() = default;

   void Init();
   void Update();
   void Draw();
   void Clear();

 private:
   struct TSpriteItem
   {
      std::unique_ptr<Engine::Objects::Sprite> sprite;
      Engine::Transform::WorldTransform transform;
      std::string name; // 識別用
   };
   std::vector<TSpriteItem> sprites_;
};
