#pragma once

#include"GameObject/GoalHouse/GoalHouseManager.h"

class GameScene;
/// <summary>
/// sceneのステート
/// </summary>
class IGameSceneState
{
 public:
   IGameSceneState() {};
   virtual ~IGameSceneState() {};

   virtual void Initialize(GameScene *scene) = 0;
   virtual void Update(GameScene *scene) = 0;
   virtual void ImGuiUpdate() {};
   virtual void Draw2d() {};

   void SetGoalHouse(weak_ptr<GoalHouseManager> g) { weak_GoalHouseManager_ = g; }
   
   weak_ptr<GoalHouseManager> weak_GoalHouseManager_;
};