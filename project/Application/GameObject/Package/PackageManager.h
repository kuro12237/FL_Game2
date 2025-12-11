#pragma once
#include "GameObject/ObjectInterface/ManagerComponent.h"
#include "Package.h"
#include "Utility/ObjectManager/GameObjectManager.h"

/// <summary>
/// 家管理
/// </summary>
class PackageManager : public ManagerComponent
{
 public:
   PackageManager() {};
   ~PackageManager() {};

   /// <summary>
   /// 初期化
   /// </summary>
   void Initialize() override;

   /// <summary>
   /// 更新
   /// </summary>
   void Update() override;

#pragma region Get
   vector<shared_ptr<Package>> GetPackages() { return package_; }
   const int32_t &GetNum() const{ return num_; }

#pragma endregion

 private:
   int32_t num_ = 1;
   string name_ = "Package";

   vector<shared_ptr<Package>> package_;

   bool isInitialize = false;

   unique_ptr<Engine::Particle::ParticleField<Engine::Particle::FieldType::FieldHitBox>> boxField_ = nullptr;
};
