#pragma once

#include "Cleyera.h"


class StageSelectUI
{
 public:
	 StageSelectUI();
 ~StageSelectUI() = default;

 void Init();

 void Update();

 void Draw();

 #pragma region Accessor 
 int GetCurrentSelectStageNum() const { return currentIndex_; }
 #pragma endregion

private:
 std::vector<uint32_t> textureHandles_;
 std::vector<std::unique_ptr<Engine::Objects::Sprite>> stageSprites_;
 std::vector<Engine::Transform::WorldTransform> stageTransforms_; 

 int currentIndex_ = 0;
 const float M_PI = 3.14159265358979323846f;

};
