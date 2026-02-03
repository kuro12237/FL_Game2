#pragma once
#include <memory>
#include <string>

#include "GameObject/ObjectInterface/ObjectComponent.h"
#include "Pch.h"
#include "Utility/ObjectManager/GameObjectManager.h"

enum class TO_Category
{
   Player,
   Vehicle,
   Static
};

struct TO_SpawnRecord
{
   std::string type;
   std::string name;
};

class TO_Base : public ObjectComponent
{
 public:
   TO_Base() = default;
   virtual ~TO_Base() = default;

   void SettTargetName(const std::string& targetName) {
	   targetName_ = targetName;
   }

 protected:
   void Bind2ExistingObj3D();

 protected:
   std::string targetName_;
};