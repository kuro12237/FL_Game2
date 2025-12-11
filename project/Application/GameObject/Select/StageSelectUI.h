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



private:
 unique_ptr<Engine::Objects::Sprite> sprite_ = nullptr;
 Engine::Transform::WorldTransform worldTransform_ = {};


};
