#include "TO_StaticObj.h"

TO_StaticObj::TO_StaticObj(const std::string &name) 
{
   TO_Base::SettTargetName(name);
}

void TO_StaticObj::Initialize()
{
   TO_Base::Bind2ExistingObj3D();
}
