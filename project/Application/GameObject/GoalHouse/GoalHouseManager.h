#pragma once
#include "GoalHouse.h"
#include "GameObject/ObjectInterface/ManagerComponent.h"
#include "Utility/ObjectManager/GameObjectManager.h"

/// <summary>
/// 家管理
/// </summary>
class GoalHouseManager : public ManagerComponent
{
 public:
   GoalHouseManager() {};
   ~GoalHouseManager() {};

   /// <summary>
   /// 初期化
   /// </summary>
   void Initialize() override;

   /// <summary>
   /// 更新
   /// </summary>
   void Update() override;


#pragma region Get
   vector<shared_ptr<GoalHouse>> GetBlocks() { return blocks_; }
   bool GetIsClear() { return isClear_; }
#pragma endregion

 private:
   string name_ = "GoalHouse";

   vector<shared_ptr<GoalHouse>> blocks_;

   bool isInitialize = false;

   bool isClear_ = false;

   unique_ptr<Engine::Particle::ParticleField<Engine::Particle::FieldType::FieldHitBox>> boxField_ = nullptr;
};
