#pragma once
#include "GameObject/ObjectInterface/ObjectComponent.h"
#include "Utility/ObjectId/GameObjectId.h"
#include "Utility/ObjectManager/GameObjectManager.h"

/// <summary>
/// 運ぶ先のブロッククラス
/// </summary>
class GoalHouse : public ObjectComponent
{
 public:
   GoalHouse() {};
   ~GoalHouse() {};

   /// <summary>
   /// 初期化
   /// </summary>
   /// <param name="グループ名"></param>
   /// <param name="番号"></param>
   void Initialize() override;

   /// <summary>
   /// 更新
   /// </summary>
   void Update() override;

   /// <summary>
   /// 当たった処理
   /// </summary>
   /// <param name="c"></param>
   void OnCollision(ObjectComponent *objData) override;

#pragma region Set

   void SetName(string name) { name_ = name; }
   void SetUnitIndex(uint32_t index) { unitNumber_ = index; }

#pragma endregion

 private:
   uint32_t unitNumber_ = 0;
};