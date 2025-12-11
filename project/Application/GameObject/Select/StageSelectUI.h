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
 int GetCurrentSelectStageNum() const { return currentIndex_ + 1; }
 #pragma endregion

private:
	bool IsLJoystickRight();
	bool IsLJoystickLeft();

private:
 std::vector<uint32_t> textureHandles_;
 std::vector<std::unique_ptr<Engine::Objects::Sprite>> stageSprites_;
 std::vector<Engine::Transform::WorldTransform> stageTransforms_; 

 std::unique_ptr<Engine::Objects::Sprite> buttonSprite_;
 Engine::Transform::WorldTransform buttonTransform_;

 int currentIndex_ = 0;
 const float M_PI = 3.14159265358979323846f;
 float joystickThreshold_ = 0.8f;
 bool prevRight_ = false;
 bool prevLeft_ = false;



};
