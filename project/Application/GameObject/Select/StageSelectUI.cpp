#include "StageSelectUI.h"
using namespace Engine::Manager;

StageSelectUI::StageSelectUI() 
{
   sprite_ = std::make_unique<Engine::Objects::Sprite>();
   
}

void StageSelectUI::Init()
{
   uint32_t noiseTexHandle = TextureManager::LoadPngTexture("GameObject/Noise/Noise.png");

   sprite_->Initialize();
   sprite_->SetTexHandle(noiseTexHandle);

   worldTransform_.Initialize();
}

void StageSelectUI::Update()
{
   worldTransform_.UpdateMatrix();
}

void StageSelectUI::Draw()
{
   sprite_->Draw(worldTransform_);
}