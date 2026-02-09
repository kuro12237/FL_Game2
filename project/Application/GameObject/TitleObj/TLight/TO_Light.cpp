#include "TO_Light.h"

void TO_Light::Initialize()
{
   this->jsonGropName_ = "TitleLight";
   this->CreateLightData();
   this->Update();
}
