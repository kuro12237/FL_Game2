#pragma once
#include "Cleyera.h"
#include "GameObject/ObjectInterface/LightComponent.h"

/// <summary>
/// ゲームのライト
/// </summary>
class TO_Light : public LightComponent
{
 public:
   TO_Light() {};
   ~TO_Light() {};

   /// <summary>
   /// 初期化
   /// </summary>
   void Initialize() override;

 private:
};
