#include "TO_Vehicle.h"

TO_Vehicle::TO_Vehicle(const std::string &name) 
{
   TO_Base::SettTargetName(name);
}

void TO_Vehicle::Initialize() 
{
   TO_Base::Bind2ExistingObj3D();
}

void TO_Vehicle::Update() {}
